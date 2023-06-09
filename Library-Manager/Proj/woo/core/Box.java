package woo.core;

import woo.core.enumeration.ServiceType;

import java.util.*;

public class Box extends Product{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920202L;

	private int _volume;
	/** map that stores box's items */
	private Map<String, Item> _items;
	private ServiceType _service;
	/** number of days to pay after purchasing this product */
	private static final int N = 5;


	/**
	 * @param id box id
	 * @param supplier - box
	 * @param price box price
	 * @param criticalValue box critical value
	 * @param serviceType level of service (NORMAL, AIR, PERSONAL, EXPRESS)
	 */
	public Box(String id, Supplier supplier, int price, int criticalValue, ServiceType service){
		super(id, supplier, price, criticalValue, N);
		_service = service;
		_items = new TreeMap<>();
	}

	/**
	 * Function that changes the volume attribute
	 * @param volume box volume
	 */
	protected void setVolume(int volume){
		_volume = volume;
	}

    /**
    * Function that returns the volume attribute
    * @return _volume
    */
	public int getVolume(){
		return _volume;
	}

    /**
    * Function that returns the Box's description
    * @return String of information
    */
	public String showProductData(){
		return "BOX|" + getID() + "|" + getSupplier().getID() + "|" + getPrice() + "|" + getCriticalValue() + "|" + getStock() + "|" + _service;
	}

	/**
   * Function that returns the list of items in this box
   * @return arrayList of items
   */
	public List<Item> getItems(){
		return new ArrayList<Item>(_items.values());
	}

	/**
  * Function that returns service attribute
  * @return _service
  */
	public ServiceType getServiceType(){
		return _service;
	}

	/**
	* Function that changes the level of service
	 * @param newservice new service type
	 */
	protected void setServiceType(ServiceType newService){
		_service = newService;
	}
}
