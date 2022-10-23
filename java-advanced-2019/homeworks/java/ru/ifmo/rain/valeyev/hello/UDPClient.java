package ru.ifmo.rain.valeyev.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketException;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

import java.util.ArrayList;
import java.util.List;

public class UDPClient implements HelloClient {
    public void run(final String host, final int port, final String prefix, final int threads, final int requests) {
        final ExecutorService pool = Executors.newFixedThreadPool(threads);
        for (int i = 0; i < threads; ++i) {
            pool.submit(() -> sendTask());
        }
        pool.shutdown();
    }

    private void sendTask() {

    }
}
