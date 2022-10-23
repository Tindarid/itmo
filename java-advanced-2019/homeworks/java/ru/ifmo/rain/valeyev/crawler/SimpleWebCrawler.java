package ru.ifmo.rain.valeyev.crawler;

import java.util.Queue;
import java.util.ArrayDeque;
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.io.IOException;

import info.kgeorgiy.java.advanced.crawler.Crawler;
import info.kgeorgiy.java.advanced.crawler.Result;
import info.kgeorgiy.java.advanced.crawler.Downloader;
import info.kgeorgiy.java.advanced.crawler.Document;
import info.kgeorgiy.java.advanced.crawler.URLUtils;

public class SimpleWebCrawler implements Crawler {
    private final Downloader downloader;

    public SimpleWebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.downloader = downloader;
    }

    public Result download(final String url, final int depth) {
        final Queue<String> queue = new ArrayDeque<>();
        final Queue<Integer> depthQueue = new ArrayDeque<>();
        final Set<String> urls = new HashSet<>();
        final Map<String, IOException> errors = new HashMap<>();
        queue.add(url);
        depthQueue.add(depth);
        while (!queue.isEmpty()) {
            final String current = queue.poll();
            final Integer currentDepth = depthQueue.poll();
            if (urls.contains(current) || errors.containsKey(current)) {
                continue;
            }
            try {
                final Document document = downloader.download(current);
                urls.add(current);
                if (currentDepth == 1) {
                    continue;
                }
                for (String link : document.extractLinks()) {
                    queue.add(link);
                    depthQueue.add(depth - 1);
                }
            } catch (IOException e) {
                errors.put(current, e);
            }
        }
        return new Result(new ArrayList<String>(urls), errors);
    }

    public void close() {
    }
}
