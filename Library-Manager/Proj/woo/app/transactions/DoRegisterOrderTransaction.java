package woo.app.transactions;

import java.util.ArrayList;
import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Form;
import pt.tecnico.po.ui.Input;
import woo.core.Request;
import woo.core.StoreManager;
import woo.app.exception.*;


/**
 * Register order.
 */
public class DoRegisterOrderTransaction extends Command<StoreManager> {

	Input<String> _supplierID;
	Input<String> _productID;
	Input<Integer> _quantity;
	Input<Boolean> _more;

  public DoRegisterOrderTransaction(StoreManager receiver) {
    super(Label.REGISTER_ORDER_TRANSACTION, receiver);
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
  }

  @Override
  public final void execute() throws DialogException {
	  	_form.parse();

	  	String supplierID = _supplierID.value();

	  	try{
	  		_receiver.checkSupplier(supplierID);
	  	}catch(woo.core.exception.UnknownSupplierKeyException uske) {
	  		throw new UnknownSupplierKeyException(uske.getKey());
	  	}

	  	List<Request> requests = new ArrayList<>();

	  	Form otherRequestsForm = new Form(_form.title());
	    _productID = otherRequestsForm.addStringInput(Message.requestProductKey());
	    _quantity = otherRequestsForm.addIntegerInput(Message.requestAmount());
	    _more = otherRequestsForm.addBooleanInput(Message.requestMore());

	  do {
		  try {
			 otherRequestsForm.parse();
			_receiver.checkRequest(supplierID, _productID.value(), _quantity.value());
			requests.add(new Request(_receiver.getProduct(_productID.value()), _quantity.value()));
		  } catch(woo.core.exception.UnknownProductKeyException upke) {
			  throw new UnknownProductKeyException(upke.getKey());
		  }catch(woo.core.exception.UnauthorizedSupplierException use) {
			  throw new UnauthorizedSupplierException(use.getKey());
		  }catch(woo.core.exception.WrongSupplierException wse) {
			  throw new WrongSupplierException(wse.getSupplierKey(), wse.getProductKey());
		  }

	  }while(_more.value() == true);

	  _receiver.registerOrder(supplierID, requests);
  }
}
