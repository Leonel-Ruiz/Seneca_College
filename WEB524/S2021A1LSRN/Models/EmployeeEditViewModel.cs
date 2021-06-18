using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace S2021A1LSRN.Models
{
    public class EmployeeEditViewModel
    {
        [Key]
        [Display(Name = "Employee Id")] //Display Attribute
        public int EmployeeId { get; set; } //Unique Identifier property

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