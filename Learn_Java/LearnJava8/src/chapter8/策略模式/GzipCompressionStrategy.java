package chapter8.策略模式;

import java.io.IOException;
import java.io.OutputStream;
import java.util.zip.GZIPOutputStream;

/**
 * Created by sunkai on 2017/12/14
 */
public class GzipCompressionStrategy implements CompressionStrategy {
    @Override
    public OutputStream compress(OutputStream data) throws IOException {
        return new GZIPOutputStream(data);
    }
}
