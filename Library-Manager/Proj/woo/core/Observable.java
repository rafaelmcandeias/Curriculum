package woo.core;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/* Observer design pattern, the entity being observed who sends notifications to the observers */
public abstract class Observable implements Serializable {

	/** Serial number for serialization. */
	private static final long serialVersionUID = 52019202087L;
	List<IObserver> _observers = new ArrayList<>();

	protected void registerObserver(IObserver obs) {
		_observers.add(obs);
	}

	protected void removeObserver(IObserver obs) {
		_observers.remove(obs);
	}

	public boolean containsObserver(IObserver obs) {
		return _observers.contains(obs);
	}

	protected void notifyObservers(Notification notification) {
		for(IObserver obs : _observers) {
			obs.update(notification);
		}
	}
}
