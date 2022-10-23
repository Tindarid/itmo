package ru.ifmo.rain.valeyev.crawler;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import java.io.IOException;
import java.net.MalformedURLException;
import java.nio.file.Paths;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

import info.kgeorgiy.java.advanced.crawler.Crawler;
import info.kgeorgiy.java.advanced.crawler.Result;
import info.kgeorgiy.java.advanced.crawler.Downloader;
import info.kgeorgiy.java.advanced.crawler.CachingDownloader;
import info.kgeorgiy.java.advanced.crawler.Document;
import info.kgeorgiy.java.advanced.crawler.URLUtils;

public class WebCrawler implements Crawler {
    private final Downloader downloader;
    private final ExecutorService downloadersPool;
    private final ExecutorService extractorsPool;
    private final int perHost;
    private final IOException defaultValue = new IOException();

    public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.downloader = downloader;
        downloadersPool = Executors.newFixedThreadPool(downloaders);
        extractorsPool = Executors.newFixedThreadPool(extractors);
        this.perHost = perHost;
    }

    public Result download(final String url, final int depth) {
        if (depth < 1) {
            throw new IllegalArgumentException("Depth value must be positive integer");
        }
        final List<String> urls = new ArrayList<>();
        final Map<String, IOException> errors = new ConcurrentHashMap<>();
        final Map<String, Integer> hosts = new ConcurrentHashMap<>();
        final AtomicInteger workers = new AtomicInteger();
        downloadTask(url, workers, errors, depth, hosts);
        while (workers.get() > 0) { 
            
        }
        for (Map.Entry<String, IOException> entry : errors.entrySet()) {
            if (entry.getValue() == defaultValue) {
                String key = entry.getKey();
                urls.add(key);
                errors.remove(key);
            }
        }
        return new Result(urls, errors);
    }

    public void close() {
        downloadersPool.shutdown();
        extractorsPool.shutdown();
    }

    private void downloadTask(final String url, final AtomicInteger workers,
                              final Map<String, IOException> result, final int depth, final Map<String, Integer> hosts) {
        workers.incrementAndGet();
        downloadersPool.execute(() -> {
            try {
                String host = URLUtils.getHost(url);
                try {
                    synchronized (result) {
                        if (result.containsKey(url)) {
                            return;
                        }
                        result.put(url, defaultValue);
                    }
                    synchronized (hosts) {
                        if (hosts.containsKey(host)) {
                            try {
                                while (hosts.get(host) == perHost) {
                                    hosts.wait();
                                }
                            } catch (InterruptedException e) {
                                //
                            }
                            hosts.put(host, hosts.get(host) + 1);
                        } else {
                            hosts.put(host, 1);
                        }
                    }
                    final Document document = downloader.download(url);
                    synchronized (hosts) {
                        hosts.put(host, hosts.get(host) - 1);
                        hosts.notifyAll();
                    }
                    if (depth > 1) {
                        extractTask(url, workers, result, depth - 1, hosts, document);
                    }
                } catch (IOException e) {
                    result.put(url, e);
                    synchronized (hosts) {
                        hosts.put(host, hosts.get(host) - 1);
                        hosts.notifyAll();
                    }
                }
            } catch (MalformedURLException e) {
                //
            } finally {
                workers.decrementAndGet();
            }
        });
    }

    private void extractTask(final String url, final AtomicInteger workers,
                             final Map<String, IOException> result, final int depth, final Map<String, Integer> hosts,
                             final Document document) {
        workers.incrementAndGet();
        extractorsPool.execute(() -> {
            try {
                for (String newUrl : document.extractLinks()) {
                    downloadTask(newUrl, workers, result, depth, hosts);
                }
            } catch (IOException e) {
                result.put(url, e);
            } finally {
                workers.decrementAndGet();
            }
        });
    }

    public void main(String[] args) {
        if (args == null || args.length != 5) {
            System.out.println("Usage: WebCrawler url [depth [downloaders [extractors [perHost]]]]");
            return;
        }
        final String url = args[0];
        final int depth = Integer.parseInt(args[1]);
        final int downloaders = Integer.parseInt(args[2]);
        final int extractors = Integer.parseInt(args[3]);
        final int perHost = Integer.parseInt(args[4]);
        try (Crawler crawler = new WebCrawler(new CachingDownloader(Paths.get(url)), downloaders, extractors, perHost)) {
            Result result = crawler.download(url, depth);
            System.out.println("Downloaded OK:");
            for (String link : result.getDownloaded()) {
                System.out.println(link);
            }
            System.out.println("Errors:");
            for (Map.Entry<String, IOException> entry : result.getErrors().entrySet()) {
                System.out.println(entry.getValue() + " " + entry.getKey());
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println(e.getMessage());
        }
    }
}
