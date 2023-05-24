const express = require("express");
const router = express.Router();
const db = require("../models");
const File = db.file;
const FileStatus = db.status;
const path = require("path");

router.get("/:uuid", async (req, res) => {
  console.log("Start downloading file from server");
  try {
    const file = await File.findOne({
      where: {
        uuid: req.params.uuid
      }
    });
    console.log("I'm here");
    if (!file) {
      return res.render("download", { error: "Link has been expired" });
    }
    file.status = FileStatus.Unclenched;
    await file.save();
    return res.render("download", {
      uuid: file.uuid,
      filesize: file.size,
      download: `${process.env.APP_BASE_URL}/api/files/download/${file.uuid}`,
    });
  } catch (err) {
    console.log("Problem in downloading with: ", err);
    return res.render("download", { error: "Something went wrong" });
  }
});

module.exports = router;
