package ru.ifmo.rain.valeyev.hello;

import java.net.DatagramPacket;
import java.net.SocketAddress;
import java.nio.charset.Charset;

public class Utils {
    private final static Charset CHARSET = Charset.forName("UTF-8");
    private final static int BUF_SIZE = 1000;

    public static DatagramPacket convert(final DatagramPacket packet) {
        String message = new String(packet.getData(), packet.getOffset(), packet.getLength(), CHARSET);
        return construct("Hello, " + message, packet.getSocketAddress());
    }

    public static DatagramPacket construct() {
        return new DatagramPacket(new byte[BUF_SIZE], BUF_SIZE);
    }

    public static DatagramPacket construct(final String message, final SocketAddress address) {
        return new DatagramPacket(message.getBytes(CHARSET), message.length(), address);
    }
}
