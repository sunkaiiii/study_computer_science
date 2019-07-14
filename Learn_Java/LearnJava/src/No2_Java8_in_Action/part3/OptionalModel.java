package No2_Java8_in_Action.part3;

import java.util.Optional;

public class OptionalModel {
    public static class Person {
        private Optional<Car> car;

        public Optional<Car> getCar() {
            return car;
        }
    }

    public static class Car {
        private Optional<Insurance> insurance;

        public Optional<Insurance> getInsurance() {
            return insurance;
        }
    }

    public static class Insurance {
        private String name;

        public String getName() {
            return name;
        }
    }
}
