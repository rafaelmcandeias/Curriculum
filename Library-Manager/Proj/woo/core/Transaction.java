package woo.core;

import java.io.Serializable;

public abstract class Transaction implements Serializable{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 52019202010L;

	private int _id;
	private static int _numTransaction;
	private int _payday;
	private double _baseValue;

	public Transaction(){
		_id = _numTransaction;
		_numTransaction++;
	}


	/**
	 * @param payday the day when the transaction was paid
	 */
	public Transaction(int payday){
		this();
		_payday = payday;
	}


	public int getPayDay(){
		return _payday;
	}

	protected void setPayDay(int payday){
		_payday = payday;
	}

	public int getID(){
		return _id;
	}

	public abstract String showTransaction(int currentDate);

	public double getBaseValue(){
		return _baseValue;
	}

	protected void setBaseValue(double value) {
		_baseValue = value;
	}

}
