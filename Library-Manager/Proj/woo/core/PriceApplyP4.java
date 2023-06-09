package woo.core;

import woo.core.enumeration.Statute;

// Fourth period payment

public class PriceApplyP4 implements IPriceApplyStrategy{
	private double _penalty;

	public void apply(Sale sl){

		Sale sale = sl;
		Client client = sale.getClient();
		int deadlineShift = sale.getDeadLineShift();
		Statute clientStatute = client.getStatute();

		if(clientStatute == Statute.NORMAL){
			_penalty = 0.1*deadlineShift;
		}else if(clientStatute == Statute.SELECTION){
			_penalty = 0.05*deadlineShift;
		}else if(clientStatute == Statute.ELITE){
			_penalty = 0;
		}

		sale.applyPenalty(_penalty);
	}
}
