const express = require('express')
const router = express.Router();


//This allows you to pefrom CRUD operations on the User colections 
const User = require("../models/User");

router.get("/", (req, res) => {

    //loads dashboard.handlebars
    res.render("Dashboard/dashboardUser")
});

module.exports=router;