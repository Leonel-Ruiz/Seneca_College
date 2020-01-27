const express = require('express')
const router = express.Router();


router.get("/",(req,res)=>{
   //This destorys the session
   req.session.destroy();
    res.redirect("/Login");

});

module.exports=router;