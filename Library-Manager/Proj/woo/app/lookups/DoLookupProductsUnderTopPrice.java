package woo.app.lookups;

import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.core.Product;
import woo.core.StoreManager;
//FIXME import other classes

/**
 * Lookup products cheaper than a given price.
 */
public class DoLookupProductsUnderTopPrice extends Command<StoreManager> {

	Input<Integer> _topPrice;

	public DoLookupProductsUnderTopPrice(StoreManager storefront) {
		super(Label.PRODUCTS_UNDER_PRICE, storefront);
		_topPrice = _form.addIntegerInput(Message.requestPriceLimit());
	}

	@Override
	public void execute() throws DialogException {
		_form.parse();

		List<Product> products = _receiver.getProductsUnderTopPrice(_topPrice.value());

		for(Product product : products) {
			_display.addLine(product.showProductData());
		}

		_display.display();
	}
}
