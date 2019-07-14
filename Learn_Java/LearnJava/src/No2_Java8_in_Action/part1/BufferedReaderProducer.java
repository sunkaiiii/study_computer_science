package No2_Java8_in_Action.part1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class BufferedReaderProducer {
    @FunctionalInterface
    interface BufferedReaderProcessor {
        String process(BufferedReader b) throws IOException;
    }

    public static String processFile(BufferedReaderProcessor p) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader("/Users/sunkai/Documents/OneDrive/手机使用时长记录.txt"))) {
            return p.process(br); //处理BufferedReader对象
        }
    }
}
