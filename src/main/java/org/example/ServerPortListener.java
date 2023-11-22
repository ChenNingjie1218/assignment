//package org.example;
//
//import org.springframework.boot.web.server.WebServerException;
//import org.springframework.boot.web.servlet.context.ServletWebServerInitializedEvent;
//import org.springframework.context.ApplicationListener;
//import org.springframework.stereotype.Component;
//
//@Component
//public class ServerPortListener implements ApplicationListener<ServletWebServerInitializedEvent>{
//
//        private static final int DEFAULT_PORT = 9527;
//        private static final int PORT_INCREMENT = 1;
//
//        @Override
//        public void onApplicationEvent(ServletWebServerInitializedEvent event) {
//        int port = event.getApplicationContext().getWebServer().getPort();
//        int newPort = getNextPort(port);
//        try {
//            event.getApplicationContext().getWebServer().stop();
//            event.getApplicationContext().getWebServer().start();
//        } catch (WebServerException e) {
//            // 处理启动服务器异常
//            e.printStackTrace();
//        }
//        System.out.println("RESTful API Server started, listening on port " + newPort);
//    }
//
//        private int getNextPort(int currentPort) {
//        return currentPort + PORT_INCREMENT;
//    }
//
//}
