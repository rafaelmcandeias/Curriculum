package woo.core;


public class Book extends Product{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920201L;

	private String _title;
	private String _author;
	private String _isbn;
	/** dias de tolerancia de pagamento */
	private static final int N = 3;

	/**
	 * @param id - book id
	 * @param supplier -- book supplier
	 * @param price book price
	 * @param criticalValue book critical value
	 * @param title book title
	 * @param author book author
	 * @param isbn book isbn
	 */
	public Book(String id, Supplier supplier, int price, int criticalValue, String title, String author, String isbn){
		super(id, supplier, price, criticalValue, N);
		_title = title;
		_author = author;
		_isbn = isbn;
	}


   /**
    * Function that returns the title attribute
    * @return _title
    */
	public String getTitle(){
		return _title;
	}

   /**
    * Function that returns the author attribute
    * @return _author
    */
	public String getAuthor(){
		return _author;
	}

	/**
     * Function that returns the isbn attribute
     * @return _tisbn
     */
	public String getIsbn(){
		return _isbn;
	}

	/**
     * Function that returns the Book's description
     * @return String of information
     */
	public String showProductData(){
		return "BOOK|" + getID() + "|" + getSupplier().getID() + "|" + getPrice() + "|" + getCriticalValue() + "|" + getStock() + "|" + _title  + "|" + _author + "|" + _isbn;
	}
}
