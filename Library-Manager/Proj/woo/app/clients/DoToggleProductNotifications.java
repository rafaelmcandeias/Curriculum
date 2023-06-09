package woo.app.clients;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.app.exception.UnknownClientKeyException;
import woo.app.exception.UnknownProductKeyException;
import woo.core.StoreManager;

/**
 * Toggle product-related notifications.
 */
public class DoToggleProductNotifications extends Command<StoreManager> {

	Input<String> _clientID;
	Input<String> _productID;

  public DoToggleProductNotifications(StoreManager storefront) {
    super(Label.TOGGLE_PRODUCT_NOTIFICATIONS, storefront);
    _clientID = _form.addStringInput(Message.requestClientKey());
    _productID = _form.addStringInput(Message.requestProductKey());
  }

  @Override
  public void execute() throws DialogException {

		_form.parse();

	  try {

		  if(_receiver.toggleProductNotifications(_clientID.value(), _productID.value())) {
			  _display.addLine(Message.notificationsOn(_clientID.value(), _productID.value()));
		  }else {
			  _display.addLine(Message.notificationsOff(_clientID.value(), _productID.value()));
		  }

		  _display.display();

	  }catch(woo.core.exception.UnknownClientKeyException ucke){
	      throw new UnknownClientKeyException(ucke.getKey());
	   }catch(woo.core.exception.UnknownProductKeyException upke){
		  throw new UnknownProductKeyException(upke.getKey());
		}
  }

}
