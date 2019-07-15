package No3_Concurrency_Programming_with_Java.cp3;

import No3_Concurrency_Programming_with_Java.cp3.model.Sample;

public interface Classifier {
    String classify(Sample example) throws Exception;

    default void destroy() {
    }
}
