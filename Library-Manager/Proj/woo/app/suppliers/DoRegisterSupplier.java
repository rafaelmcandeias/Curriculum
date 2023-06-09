package woo.app.suppliers;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.DuplicateSupplierKeyException;

/**
 * Register supplier.
 */
public class DoRegisterSupplier extends Command<StoreManager> {

  Input<String> _supplierID;
  Input<String> _supplierName;
  Input<String> _supplierAddress;

  public DoRegisterSupplier(StoreManager receiver) {
    super(Label.REGISTER_SUPPLIER, receiver);
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
    _supplierName = _form.addStringInput(Message.requestSupplierName());
    _supplierAddress = _form.addStringInput(Message.requestSupplierAddress());
  }

  @Override
  public void execute() throws DialogException {
    _form.parse();

    try{
      _receiver.registerSupplier(_supplierID.value(), _supplierName.value(), _supplierAddress.value());
    } catch(woo.core.exception.DuplicateSupplierKeyException dske){
        throw new DuplicateSupplierKeyException(dske.getKey());
    }
  }
}
