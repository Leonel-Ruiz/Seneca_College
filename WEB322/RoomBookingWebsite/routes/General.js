const express = require('express')
const router = express.Router();

/*GENERAL ROUTES*/
//Route to direct user to home page
router.get("/", (req, res) => 
{
    res.render("General/home")
});

router.post("/home", (req, res) => {

    res.send("Hello, you are going to");
    const country = req.body.where;
    console.log(`${country}`);
});

module.exports=router;