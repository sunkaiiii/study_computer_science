package java8_in_action.part3;

public class Quote {

    private final String shopName;
    private final double price;
    private final Shop.Code discountCode;

    public Quote(String shopName, double price, Shop.Code code) {
        this.shopName = shopName;
        this.price = price;
        this.discountCode = code;
    }

    public static Quote parse(String s) {
        String[] split = s.split(":");
        String shopName = split[0];
        double price = Double.parseDouble(split[1]);
        Shop.Code discountCode = Shop.Code.valueOf(split[2]);
        return new Quote(shopName, price, discountCode);
    }

    public String getShopName() {
        return shopName;
    }

    public double getPrice() {
        return price;
    }

    public Shop.Code getDiscountCode() {
        return discountCode;
    }
}
