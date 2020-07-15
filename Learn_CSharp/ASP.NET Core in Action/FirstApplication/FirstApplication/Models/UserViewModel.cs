using System;
using System.ComponentModel.DataAnnotations;

namespace FirstApplication.Models
{
    public class UserViewModel
    {
        //Values marked by DataAnotation attributes
        [Required]
        [StringLength(100)]
        [Display(Name = "Your name")]
        public string FirstName { get; set; }
        [Required]
        [StringLength(100)]
        [Display(Name = "Last name")]
        public string LastName { get; set; }
        [Required]
        [EmailAddress]
        public string Email { get; set; }
        [Phone]
        [Display(Name = "Phone number")]
        public string PhoneNumber { get; set; }

        public string Dec { get; set; }
        public string Multiline { get; set; }
    }
}
