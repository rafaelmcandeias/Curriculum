package woo.core;

// First period payment
public class PriceApplyP1 implements IPriceApplyStrategy{
	private double _discount = 0.1;

	public void apply(Sale sl){
		Sale sale =  sl; 
		sale.applyDiscount(_discount);
	}

}
