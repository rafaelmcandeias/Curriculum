package woo.core;

import woo.core.enumeration.Statute;

// Second period payment
public class PriceApplyP2 implements IPriceApplyStrategy{
	private double _discount;

	public void apply(Sale sl){

		Sale sale = sl;
		Client client = sale.getClient();
		Statute clientStatute = client.getStatute();

		if(clientStatute == Statute.NORMAL){
			_discount = 0;
		}else if(clientStatute == Statute.SELECTION){
			int deadLineShift = sale.getDeadLineShift();

			if(deadLineShift >= 2){
				_discount = 0.05;
			}else{
				_discount = 0;
			}
		}else if(clientStatute == Statute.ELITE){
			_discount = 0.1;
		}

		sale.applyDiscount(_discount);

	}
}
