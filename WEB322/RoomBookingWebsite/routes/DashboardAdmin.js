const express = require('express')
const router = express.Router();

const Room = require("../models/Room");

const Location = require('../models/Location');


//This allows you to pefrom CRUD operations on the User colections 
const User = require("../models/User");

router.get("/", (req, res) => {

    //loads dashboard.handlebars
    res.render("Dashboard/dashboardAdmin")
});

router.post("/", (req, res) => {
 
    const formData = {
        title: req.body.title,
        price: req.body.price,
        description: req.body.description,
        location: req.body.location
    };

    const errors = [];
    
    if (req.files == null) {
        errors.push(`Image upload required`)
    } 
    else 
    {
        if (req.files.roomImages.mimetype.indexOf("image") == -1) 
        {
            errors.push("sorry, please upload only image-example:jpeg,gif,png")
        }
    }
    if (errors.length > 0) {
        res.render("Room/addRoom", {
            title: formData.title,
            price: formData.price,
            description: formData.description,
            location: formData.location
        });
    }
    else {
        const room = new Room(formData);
        room.save()
            .then(() => {
                //rename file to include the userid
                req.files.roomImages.name = `room_${room._id}${path.parse(req.files.roomImage.name).ext}`
                //upload file to server
                req.files.roomImages.mv(`public/room/${req.files.roomImage.name}`)
                    .then(() => {
                        //needed to refer to associate the uplated picture 
                        Room.findByIdAndUpdate(room._id, {
                            roomImages: req.files.roomImage.name
                        })
                        .catch(err => {
                            console.log(`Error :${err}`)
                        });
                        then(() => {
                            console.log(`File name was updated in the database`)
                            res.render("Dashboard/dashboardAdmin");
                        })
                            .catch(err => {
                                console.log(`Error :${err}`)
                            });
                    });
            })
            .catch(err => { console.log(`Error :${err}`) });
    }
    
  res.redirect("Dashboard/dashboardAdmin");
});



module.exports=router;