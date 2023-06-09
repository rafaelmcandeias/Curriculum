package woo.core;

import java.io.Serializable;

import woo.core.enumeration.NotificationDescription;
import woo.core.enumeration.DeliveryMode;

public class Notification implements Serializable{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920205L;

	private Product _product;
	private NotificationDescription _description;
	private DeliveryMode _delivery;

	/**
	 * @param productID product id
	 * @param description notification description
	 */
	public Notification(Product product, NotificationDescription description){
		_product = product;
		_description = description;
		_delivery = DeliveryMode.APP;
	}

	/**
    * Function that returns the product id associated to the notification
    * @return _product
    */
	public String getProductID(){
		return _product.getID();
	}

	/**
    * Function that returns the notification's description
    * @return _description
    */
	public NotificationDescription getDescription(){
		return _description;
	}

	/**
    * Function that returns the notification's information
    * @return String of information
    */
	public String showNotification(){
		return _description + "|" + _product.getID() + "|" + _product.getPrice();
	}

	/**
    * Function that returns the notification's delivery mode
    * @return _delivery
    */
	public DeliveryMode getDelivery(){
		return _delivery;
	}

	public void setDelivery(DeliveryMode delivery){
		_delivery = delivery;
	}
}
