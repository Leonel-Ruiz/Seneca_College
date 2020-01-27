/********************************************************************************* 
* 
* WEB222 – Assignment #4A 
* 
* I declare that this assignment is my own work in accordance with Seneca 
* Academic Policy. No part of this assignment has been copied manually or 
* electronically from any other source (including web sites) or distributed to 
* other students. 
* 
* Name: Leonel Said Ruiz Navarrete   Student ID: 104657184  Date: July 17th,2019
* 
********************************************************************************/

var filterType = ""; // sets the filter type to "" (will later be dog, cat or bird)
var filterAgeMin = 0; // sets the filter age min to 0 (for no minimum age filter)
var filterAgeMax = Number.MAX_VALUE; // sets the filter age max to the largest number possible (for no maximum age filter)

window.onload=loadTableWithFilters();

function loadTableWithFilters() 
{
    
    var PetsTable = document.getElementById('main-table-body');
    PetsTable.innerHTML = "";
    var i;
    for (i = 0; i < petData.length; i++) 
    {

        if ((filterType == "cat" && petData[i].type == "cat") || (filterType == "dog" && petData[i].type == "dog") || (filterType == "bird" && petData[i].type == "bird")||(filterType == "") ) 
        {

            if (petData[i].age <= filterAgeMax && petData[i].age >= filterAgeMin) 
            {
                var row            = document.createElement("tr");
                var textCell       = document.createElement("td");
                var imageCell      = document.createElement("td");
                var imgData        = document.createElement("img");
                var name           = document.createElement("h4");
                var petDescription = document.createElement("p");
                var petAge         = document.createElement("span");

                imgData.src = petData[i].image.src;
                imgData.alt = petData[i].image.alt;
                imgData.height = petData[i].image.height;
                imgData.width = petData[i].image.width;
                imageCell.appendChild(imgData);

                row.appendChild(imageCell);

                name.appendChild(document.createTextNode(petData[i].name));
                textCell.appendChild(name);

                petDescription.innerHTML = petData[i].description;
                textCell.appendChild(petDescription);

                petAge.appendChild(document.createTextNode("Age: " + petData[i].age + " years old."));
                textCell.appendChild(petAge);
                
                row.appendChild(textCell);

                PetsTable.appendChild(row);
            }
        }
    }
}

function filterDog()
{
    filterType="dog";
    filterAgeMin=0;
    filterAgeMax=Number.MAX_VALUE;
    loadTableWithFilters();
}

function filterCat() 
{
    filterType="cat";
    filterAgeMin=0;
    filterAgeMax=Number.MAX_VALUE;
    loadTableWithFilters();
}

function filterBird()
{
    filterType="bird";
    filterAgeMin=0;
    filterAgeMax=Number.MAX_VALUE;
    loadTableWithFilters();
}

function filter_zero_1() 
{
   filterType="";
   filterAgeMin=0;
   filterAgeMax=1;
   loadTableWithFilters();
}

function filter_1_3()
{
    filterType="";
    filterAgeMin=1;
    filterAgeMax=3;
    loadTableWithFilters();
}

function filter_4_plus() 
{
    filterType="";
    filterAgeMin=4;
    filterAgeMax=Number.MAX_VALUE;
    loadTableWithFilters();
}

function filterAllPets()
{
    filterType="";
    filterAgeMin=0;
    filterAgeMax=Number.MAX_VALUE;
    loadTableWithFilters();
}