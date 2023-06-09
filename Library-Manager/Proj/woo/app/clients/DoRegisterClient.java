package woo.app.clients;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.DuplicateClientKeyException;

/**
 * Register new client.
 */
public class DoRegisterClient extends Command<StoreManager> {

  Input<String> _clientID;
  Input<String> _clientName;
  Input<String> _clientAddress;

  public DoRegisterClient(StoreManager storefront) {
    super(Label.REGISTER_CLIENT, storefront);
    _clientID = _form.addStringInput(Message.requestClientKey());
    _clientName = _form.addStringInput(Message.requestClientName());
    _clientAddress = _form.addStringInput(Message.requestClientAddress());
  }

  @Override
  public void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.registerClient(_clientID.value(), _clientName.value(), _clientAddress.value());
    } catch(woo.core.exception.DuplicateClientKeyException dcke){
      throw new DuplicateClientKeyException(dcke.getKey());
    }
  }

}
