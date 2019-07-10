package java8_in_action.part3;

import javax.xml.validation.Validator;

public class StrategyModel {
    public interface ValidationStrategy{
        boolean execute(String s);
    }

    public static class IsAllLowerCase implements ValidationStrategy{
        @Override
        public boolean execute(String s) {
            return s.matches("[a-z]+");
        }
    }

    public static class IsNumeric implements ValidationStrategy{
        @Override
        public boolean execute(String s) {
            return s.matches("\\d+");
        }
    }

    private final ValidationStrategy strategy;

    public StrategyModel(ValidationStrategy v){
        this.strategy=v;
    }

    public boolean validate(String s){
        return strategy.execute(s);
    }
}
