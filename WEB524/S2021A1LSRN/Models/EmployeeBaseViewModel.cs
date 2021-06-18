using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace S2021A1LSRN.Models
{
    //This class is used to define the data that the web app passes to the view and displays in
    //the web browser.In other words, it is used to get data from the web app to the user.
    public class EmployeeBaseViewModel : EmployeeAddViewModel
    {
        [Key]
        [Display(Name = "Employee Id")] //Display Attribute
        public int EmployeeId { get; set; }
    }
}