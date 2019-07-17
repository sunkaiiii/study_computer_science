package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp4;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class NewsWriter implements Runnable {
    //写入磁盘
    //他将作为一个独立线程运行
    private NewsBuffer buffer;
    public NewsWriter(NewsBuffer buffer){
        this.buffer=buffer;
    }

    @Override
    public void run() {
        //每次从buffer的实例当中获取一个元素
        //如果缓存为空，则线程将被阻塞
        try{
            while(!Thread.currentThread().isInterrupted()){
                var item=buffer.get();
                Path path= Paths.get("output/"+item.getFileName());
                try(var fileWriter= Files.newBufferedWriter(path, StandardOpenOption.CREATE)){
                    fileWriter.write(item.toString());
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }catch (InterruptedException ignore){}
    }
}
