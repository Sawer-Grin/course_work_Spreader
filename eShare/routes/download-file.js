const express = require("express");
const router = express.Router();
const db = require("../models");
const File = db.file;
const StatusFile = db.status;
const path = require("path");
const fs = require('fs-extra');
const { route } = require("./files");

router.get("/:uuid", async (req, res) => {
  const folder = await File.findOne({
    where: {
      uuid: req.params.uuid
    } 
  });
  if (!folder) {
    return res.render("download", { error: "Link has been expired" });
  }
  folder.status = StatusFile.Saved;
  await folder.save();
  const directory_path = `${__dirname}/../temp/${folder.uuid}/`;
  fs.readdir(directory_path, (err, files) => {
    if (err) {
      return console.log("Problem with reading directory for sending client files. Message: ", err);
    }
    files.forEach(function (file) {
      console.log("Name for client's file: ", file);
      res.download(`${directory_path}/${file}`);
    });
  })
  fs.remove(directory_path, (err) => {
    if (err) 
      return console.error(err);
    console.log('success!');
  });
});

module.exports = router;
