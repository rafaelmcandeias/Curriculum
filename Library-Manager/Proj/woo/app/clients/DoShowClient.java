package woo.app.clients;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import java.util.List;
import java.util.ArrayList;

import woo.core.Client;
import woo.core.StoreManager;
import woo.core.Notification;


import woo.app.exception.UnknownClientKeyException;

/**
 * Show client.
 */
public class DoShowClient extends Command<StoreManager> {


  private Input<String> _clientID;

  public DoShowClient(StoreManager storefront) {
    super(Label.SHOW_CLIENT, storefront);

    _clientID = _form.addStringInput(Message.requestClientKey());
  }

  @Override
  public void execute() throws DialogException {

    _form.parse();

    try{

      Client client = _receiver.getClient(_clientID.value());
      List<Notification> notifications = client.getNotifications();

      _display.addLine(client.showClientData());

      for(Notification notification : notifications){
        _display.addLine(notification.showNotification());
      }
      _display.display();

      _receiver.clearNotifications(client);

    } catch(woo.core.exception.UnknownClientKeyException ucke){
      throw new UnknownClientKeyException(ucke.getKey());
    }
  }

}
