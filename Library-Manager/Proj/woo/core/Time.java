package woo.core;

import java.io.Serializable;

public class Time implements Serializable{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920209L;

	private int _date;

	public Time(){}


	/**
	 * @param numberOfDays number of days to advance
	 */
	protected void advanceDate(int numberOfDays){
		_date += numberOfDays;
	}

	public int getCurrentDate(){
		return _date;
	}
}
