package woo.core;

import java.io.Serializable;

public interface IObserver extends Serializable {
	/**
	* @param notification to send to the observers
	*/
	void update(Notification notification);
}
