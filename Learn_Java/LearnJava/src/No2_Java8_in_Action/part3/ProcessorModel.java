package No2_Java8_in_Action.part3;

public class ProcessorModel {
    public static class HeaderTextProcessing extends ProcessingObject<String>{
        @Override
        protected String handleWork(String input) {
            return "From Raoul, Mario and Alan: "+ input;
        }
    }

    public static class SpellCheckerProcessing extends ProcessingObject<String>{
        @Override
        public String handleWork(String input) {
            return input.replaceAll("labda","lambda");
        }
    }
}
