package woo.core;

import woo.core.enumeration.Period;

public class Sale extends Transaction {
	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920207L;

	private Product _product;
	private Client _client;
	/** last valid date to make payment with no charge */
	private int _paymentDeadline;
	/** boolean that tells if the Client has already paid */
	private boolean _isPaid;
	/** last valid day to pay without any fee */
	private int _deadLineShift;
	private int _quantity;
	/** store the amount of money already paid by client */
	private double _paidValue;
	private double _currentPaymentValue;
	private Period _period;
	private IPriceApplyStrategy _applyPriceStrategy;


	/**
   * @param client
   * @param paymentDeadLine
   * @param product
   * @param quantity
   */
	public Sale(Client client, int paymentDeadline, Product product, int quantity){
		_quantity = quantity;
		_client = client;
		_product = product;
		_paymentDeadline = paymentDeadline;
		setBaseValue(_product.getPrice() * _quantity);
		_currentPaymentValue = _product.getPrice() * _quantity;
		_applyPriceStrategy = new PriceApplyP1();
		_period = Period.P1;
	}

	/**
   * Function that shows the sale description
   * @return String of information
   */
	public String showTransaction(int currentDate){
		computeSalePeriodPrice(currentDate);
		_paidValue = _currentPaymentValue;
		String format = "";
		format+= getID() + "|" + _client.getID() + "|" + _product.getID() + "|" + _quantity + "|" + (int) Math.round(getBaseValue()) + "|" + (int) Math.round(_paidValue) + "|" + _paymentDeadline;

		if(_isPaid){
			format += "|" + getPayDay();
		}

		return format;
	}


	public void computeSalePeriodPrice(int currentDate) {

		int nDays = _product.getNDays();
		int firstInterval = _paymentDeadline - currentDate;
		int secondInterval = currentDate - _paymentDeadline;


		if(firstInterval >= nDays){
			_period = Period.P1;
			_deadLineShift = firstInterval;
			_applyPriceStrategy = new PriceApplyP1();
		}else if(firstInterval >= 0 && firstInterval < nDays){
			_period = Period.P2;
			_deadLineShift = firstInterval;
			_applyPriceStrategy = new PriceApplyP2();
		}else if(secondInterval > 0 && secondInterval <= nDays){
			_period = Period.P3;
			_deadLineShift = secondInterval;
			_applyPriceStrategy = new PriceApplyP3();
		}else if(secondInterval > nDays){
			_period = Period.P4;
			_deadLineShift = secondInterval;
			_applyPriceStrategy = new PriceApplyP4();
		}

		applyPriceStrategy();

	}

	/**
   * Function that returns the period atribute
   * @return _period
   */
	public Period getPeriod() {
		return _period;
	}

	/**
   * Function that changes the period attribute
   * @param period
   */
	protected void setPeriod(Period period) {
		_period = period;
	}

	protected void applyPriceStrategy(){
		_applyPriceStrategy.apply(this);
	}

	protected void setApplyPriceStrategy(IPriceApplyStrategy applyPriceStrategy){
		_applyPriceStrategy = applyPriceStrategy;
	}

	protected void setPaid(){
		_paidValue = _currentPaymentValue;
		setIsPaid(true);
	}

	protected void setDeadLineShift(int deadLineShift){
		_deadLineShift = deadLineShift;
	}

	/**
   * Function that returns the current payment value atribute
   * @return _current payment value
   */
	public double getCurrentPaymentValue() {
		return _currentPaymentValue;
	}

	protected void setCurrentPaymentValue(double value) {
		_currentPaymentValue = getBaseValue() + value;
	}

	/**
   * Function that returns the quantity atribute
   * @return _quantity
   */
	public int getQuantity(){
		return _quantity;
	}

	/**
   * Function that returns the dead line shift atribute
   * @return _deadlineshift
   */
	public int getDeadLineShift(){
		return _deadLineShift;
	}

	/**
   * Function that returns the quantity atribute
   * @return _quantity
   */
	public Product getProduct(){
		return _product;
	}

	protected void setIsPaid(boolean paid){
		_isPaid = paid;
	}

	public boolean isPaid(){
		return _isPaid;
	}

	public int getPaymentDeadLine(){
		return _paymentDeadline;
	}

	protected void applyPenalty(double penalty){
		setCurrentPaymentValue(getBaseValue()*penalty);
	}

	protected void applyDiscount(double discount){
		setCurrentPaymentValue(-getBaseValue()*discount);
	}

	public Client getClient(){
		return _client;
	}

	public double getPaidValue(){
		return _paidValue;
	}

	/*
	*/
	protected void setPaidValue(double value){
		_paidValue = value;
	}

}
