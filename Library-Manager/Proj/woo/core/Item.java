package woo.core;

import java.io.Serializable;

public class Item implements Serializable{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 52019202011L;

	private String _id;

	/**
	 * @param id item id
	 */
	public Item(String id){
		_id = id;
	}

	/**
    * Function that returns the id attribute
    * @return _id
    */
	public String getID(){
		return _id;
	}
}
