package cp2;

import java.io.IOException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Paths;

public class CustomClassloadingExamples {
    //类加载和反射自定义类的结合使用
    public static class Diskloader extends ClassLoader {
        public Diskloader() {
            super(Diskloader.class.getClassLoader());
        }

        public Class<?> loadFromDisk(String clzName) throws IOException {
            byte[] b = Files.readAllBytes(Paths.get(clzName));
            return defineClass(null, b, 0, b.length);
        }
    }

    public void findDeprecatedMethods(Class<?> clz) {
        for (Method m : clz.getMethods()) {
            for (var a : m.getAnnotations()) {
                if (a.annotationType() == Deprecated.class) {
                    System.out.println(m.getName());
                }
            }
        }
    }
}
