package woo.app.lookups;

import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.app.exception.UnknownClientKeyException;
import woo.core.Sale;
import woo.core.StoreManager;


/**
 * Lookup payments by given client.
 */
public class DoLookupPaymentsByClient extends Command<StoreManager> {

	private Input<String> _clientID;

	public DoLookupPaymentsByClient(StoreManager storefront) {
		super(Label.PAID_BY_CLIENT, storefront);
		_clientID = _form.addStringInput(Message.requestClientKey());
	}

	@Override
	public void execute() throws DialogException {
		_form.parse();

		try {
			List<Sale> salesPaid = _receiver.getClientPaidPurchases(_clientID.value());

			for(Sale sale : salesPaid) {
				_display.addLine(sale.showTransaction(_receiver.getCurrentDate()));
			}

			_display.display();

		}catch(woo.core.exception.UnknownClientKeyException ucke) {
			throw new UnknownClientKeyException(ucke.getKey());
		}
	}

}
