/*********************************************************************************
* WEB422 – Assignment 2
* I declare that this assignment is my own work in accordance with Seneca Academic Policy.
* No part of this assignment has been copied manually or electronically from any other source
* (including web sites) or distributed to other students. *
* Name: Leonel Said Ruiz Navarrete     Date: January 31st, 2020
*
********************************************************************************/

// saleData (array)
let saleData = [];

//page (number)
let page = 1;

// perPage (number), how many sale items we wish to view on each page
const perPage = 10;

// saleTableTemplate (Lodash template)
const saleTableTemplate = _.template
(
    `<% _.forEach(saleData, function(sales) 
    { %>
        <tr data-id=<%- sales._id %>>
            <td><%- sales.customer.email %></td>
            <td><%- sales.storeLocation %></td>
            <td><%- sales.items.length %></td>
            <td><%- moment.utc(sales.saleDate).local().format("LLLL") %></td>
        </tr>
    <% }); 
    %>`
);

// saleModelBodyTemplate (Lodash template)
const saleModalBodyTemplate = _.template(
    `<h4>Customer</h4>
    <strong>email:</strong> <%- obj.customer.email %><br>
    <strong>age:</strong> <%- obj.customer.age %><br>
    <strong>satisfaction:</strong> <%- obj.customer.satisfaction %> / 5
    <br><br>
    <h4>Items: $<%- obj.total.toFixed(2) %></h4>
    <table class="table">
        <thead>
            <tr>
                <th>Product Name</th>
                <th>Quantity</th>
                <th>Price</th>
            </tr>
        </thead>
        <tbody>
            <% _.forEach(obj.items, function(sales) { %>
                <tr data-id=<%- sales._id %>>
                    <td><%- sales.name %></td>
                    <td><%- sales.quantity %></td>
                    <td>$<%- sales.price %></td>
                </tr>
            <% }); %>
        </tbody>
    </table>`
);

// function loadSaleData()
function loadSaleData() 
{
    fetch(`https://assignment-number-one.herokuapp.com/api/sales?page=${page}&perPage=${perPage}`)
        .then((herokuData) =>
        {
            return herokuData.json();
        })
        .then((herokuJson) => 
        {
            saleData = herokuJson;
            let templateData = saleTableTemplate(saleData);
            $("#sale-table tbody").html(templateData);
            $("#current-page").html(page);
        })
}

//The following code to be executed when the document is ready 
$(function()
 {
    //populate our table with dataand set the current working page
    loadSaleData();
});

//wire up click events for all <tr> elements contained within the <tbody> of our main "sale-table"
//The purpose of this event is to show a more detailed view of the sale to the user in a Bootstrap modal window
$("#sale-table tbody").on("click","tr",function()
 {
     //stores the "id" of the clicked row in a local variable
    let clickedId = $(this).attr("data-id");

    //uses this clickedId value to find the matching sale document within the "saleData" array
    let clickedSale = saleData.find( ({ _id}) => _id == clickedId);
    
    //Next, we must assign a new property to our "clickedSale" called "total". This property will 
    //contain the total cost of all items in the sale.
    clickedSale.total = 0;

    //To calculate this value, we can loop through the "items" array in the "clickedSale" and add up 
    //the cost of all items using the formula total += (price * quantity) for every item.
    for (let i = 0; i < clickedSale.items.length; i++)
    {
        clickedSale.total += clickedSale.items[i].price * clickedSale.items[i].quantity;
    }
    
    //sets the HTML for the modal-title of the "sale-modal" to read "Sale: _id" where _id is the _id value of the "clickedSale"
    $("#sale-modal h4").html(`Sale: ${clickedSale._id}`);

    //invoke the saleModalBodyTemplate() function with the value of the "clickedSale" to obtain the full HTML
    // code (as outlined above). Take this HTML and add it as the content of the modal-body of the "sale-modal".
    $("#modal-body").html(saleModalBodyTemplate(clickedSale));

    //show the modal by selecting it using jQuery and invoking the .modal() function such that the user cannot
    // dismiss the modal by hitting "esc" on the keyboard, or clicking on the modal "backdrop".
    $('#sale-modal').modal( 
        {
            keyboard: false,
            backdrop: 'static'
        }
    );
});

// Wire up a click event for the "previous-page" button (HINT: This can be done by selecting the correct element and using the ".on()" method).
$("#previous-page").on("click", function()
 {
    if (page > 1)
     {
        page--;
    }
    loadSaleData();
});

// Wire up a click event for the "next-page" button
$("#next-page").on("click", function() 
{
    page++;
    loadSaleData();
});
