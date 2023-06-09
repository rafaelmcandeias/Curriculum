package woo.core;

import woo.core.enumeration.Statute;

// Third period payment

public class PriceApplyP3 implements IPriceApplyStrategy{
	private double _discount;
	private double _penalty;

	public void apply(Sale sl){

		Sale sale = sl;
		Client client = sale.getClient();
		int deadLineShift = sale.getDeadLineShift();
		Statute clientStatute = client.getStatute();


		if(clientStatute == Statute.NORMAL){
			_penalty = 0.05*deadLineShift;
		}else if(clientStatute == Statute.SELECTION){
			if(deadLineShift <= 1){
				_penalty = 0;
			}else{
				_penalty = 0.02;
			}
		}else if(clientStatute == Statute.ELITE){
			_discount = 0.05;
		}

		sale.applyDiscount(_discount);
		sale.applyPenalty(_penalty);

	}

}
