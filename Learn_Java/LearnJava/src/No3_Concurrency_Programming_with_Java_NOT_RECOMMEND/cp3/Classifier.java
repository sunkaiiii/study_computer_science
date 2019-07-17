package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.model.Sample;

public interface Classifier {
    String classify(Sample example) throws Exception;

    default void destroy() {
    }
}
