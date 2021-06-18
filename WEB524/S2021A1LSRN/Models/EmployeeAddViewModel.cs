using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace S2021A1LSRN.Models
{
    //The EmployeeAddViewModel class is used to define the data that the user sends (using HTTP POST) from the
    //HTML Form.In summary, it is used to get data from the user to the web app.
    public class EmployeeAddViewModel
    {
        //Constructor
        public EmployeeAddViewModel()
        {
            BirthDate = DateTime.Now.AddYears(-30);
            HireDate = DateTime.Now;
        }

        [Required]
        [StringLength(20)]
        [Display(Name = "Last Name")] //Display Attribute
        public string LastName { get; set; }

        [Required]
        [StringLength(20)]
        [Display(Name ="First Name")]
        public string FirstName { get; set; }

        [StringLength(30)]
        public string Title { get; set; }

        [Display(Name = "Birth Date")]
        public DateTime? BirthDate { get; set; }

        [Display(Name = "Hire Date")]
        public DateTime? HireDate { get; set; }

        [StringLength(70)]
        public string Address { get; set; }

        [StringLength(40)]
        public string City { get; set; }

        [StringLength(40)]
        [Display(Name = "Province")]
        public string State { get; set; }

        [StringLength(40)]
        public string Country { get; set; }

        [StringLength(10)]
        [Display(Name = "Postal Code")]
        public string PostalCode { get; set; }

        [StringLength(24)]
        [Display(Name = "Phone Number")]
        public string Phone { get; set; }

        [StringLength(24)]
        [Display(Name = "Fax Number")]
        public string Fax { get; set; }

        [StringLength(60)]
        [Display(Name = "Email Address")]
        public string Email { get; set; }
    }
}