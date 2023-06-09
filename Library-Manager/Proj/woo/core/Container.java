package woo.core;

import woo.core.enumeration.ServiceType;
import woo.core.enumeration.ServiceLevel;

import java.util.*;

public class Container extends Product{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920204L;

	private int _volume;
	private Map<String, Item> _items;
	private ServiceType _serviceType;
	private ServiceLevel _serviceLevel;
	/** number of days to pay after purchasing this product */
	private static final int N = 8;

	/**
	 * @param id container id
	 * @param supplier - container supplier
	 * @param price container price
	 * @param criticalValue container critical value
	 * @param serviceType type of service (NORMAL, AIR, PERSONAL, EXPRESS)
	 * @param serviceLevel quality of service (B4, C4, C5, DL)
	 */
	public Container(String id, Supplier supplier, int price, int criticalValue, ServiceType serviceLevel, ServiceLevel serviceQuality){
		super(id, supplier, price, criticalValue, N);
		_serviceType = serviceLevel;
		_serviceLevel = serviceQuality;
	}

	/**
  * Function changes the volume attribute
  * @param volume - container volume
  */
	protected void setVolume(int volume){
		_volume = volume;
	}

	/**
  * Function that changes the volume attribute
  * @return _volume
  */
	public int getVolume(){
		return _volume;
	}

	/**
  * Function that returns the Container's description
  * @return String of information
  */
	public String showProductData(){
		return "CONTAINER|" + getID() + "|" + getSupplier().getID() + "|" + getPrice() + "|" + getCriticalValue() + "|" + getStock() + "|" + _serviceType + "|" + _serviceLevel;
	}

	/**
  * Function that returns the list of all items
  * @return list of items
  */
	public List<Item> getItems(){
		return Collections.unmodifiableList(new ArrayList<Item>(_items.values()));
	}

	/**
  * Function that returns the service type attribute
  * @return service type
  */
	public ServiceType getServiceType(){
		return _serviceType;
	}

	/**
    * Function that returns the service level attribute
    * @return service level
    */
	public ServiceLevel getServiceLevel(){
		return _serviceLevel;
	}


	/**
    * Function that changes the service level attribute
    * @param serviceLevel service
    */
	protected void setServiceLevel(ServiceLevel serviceLevel){
		_serviceLevel = serviceLevel;
	}

	/**
    * Function that changes the type of service attribute
    * @param serviceType new level of service
    */
	protected void setServiceType(ServiceType serviceType){
		_serviceType = serviceType;
	}


}
