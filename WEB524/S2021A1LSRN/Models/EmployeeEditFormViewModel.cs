using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace S2021A1LSRN.Models
{
    public class EmployeeEditFormViewModel
    {
        [Key]
        [Display(Name = "Employee Id")] //Display Attribute
        public int EmployeeId { get; set; } //Unique Identifier property

        [Required]
        [StringLength(20)]
        [Display(Name = "Last Name")]
        public string LastName { get; set; }

        [Required]
        [StringLength(20)]
        [Display(Name = "First Name")]
        public string FirstName { get; set; }

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

        [DataType(DataType.Password)]
        public string Password { get; set; }

        [StringLength(9, MinimumLength = 9)]
        [Display(Name = "Employee Number")]
        public string EmployeeNumber { get; set; }

        [Range(1, 10, ErrorMessage = "Oficce Level must be between 1 and 10")]
        [Display(Name = "Office Level")]
        public int OfficeLevel { get; set; }
    }
}