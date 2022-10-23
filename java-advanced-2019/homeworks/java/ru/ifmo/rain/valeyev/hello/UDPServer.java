package ru.ifmo.rain.valeyev.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketException;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

import java.util.ArrayList;
import java.util.List;

public class UDPServer implements HelloServer {
    private List<DatagramSocket> sockets;
    private List<ExecutorService> pools;

    public UDPServer() {
        sockets = new ArrayList<>();
        pools = new ArrayList<>();
    }

    public void start(int port, int threads) {
        try {
            final DatagramSocket socket = new DatagramSocket(port);
            final ExecutorService pool = Executors.newFixedThreadPool(threads);
            sockets.add(socket);
            pools.add(pool);
            pool.execute(() -> receiveTask(socket, pool));
        } catch (SocketException e) {
            System.err.println(e.getMessage());
        }
    }

    private void receiveTask(final DatagramSocket socket, final ExecutorService pool) {
        while (!socket.isClosed()) {
            final DatagramPacket packet = Utils.construct();
            try {
                socket.receive(packet);
                pool.execute(() -> sendTask(socket, packet));
            } catch (Exception e) {

            }
        }
    }

    private void sendTask(final DatagramSocket socket, final DatagramPacket receivedPacket) {
        try {
            socket.send(Utils.convert(receivedPacket));
        } catch (Exception e) {

        }
    }

    public void close() {
        for (DatagramSocket socket : sockets) {
            socket.close();
        }
        for (ExecutorService pool : pools) {
            pool.shutdown();
        }
    }
}
