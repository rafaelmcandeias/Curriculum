package woo.app.clients;

import java.util.Iterator;
import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;

import woo.core.Client;
import woo.core.StoreManager;

/**
 * Show all clients.
 */
public class DoShowAllClients extends Command<StoreManager> {

  public DoShowAllClients(StoreManager storefront) {
    super(Label.SHOW_ALL_CLIENTS, storefront);
  }

  @Override
  public void execute() throws DialogException {

    List<Client> clients = _receiver.getClients();
    Iterator<Client> itr = clients.iterator();

    while(itr.hasNext()){
  	  Client client = itr.next();
  	  _display.addLine(client.showClientData());
    }
    _display.display();
  }
}
