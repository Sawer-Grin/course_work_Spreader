const express = require("express");
const router = express.Router();
const path = require("path");
const { v4: uuidv4 } = require('uuid');
const fs = require('fs-extra');
// to handle multipart/application data
// in our case to handle the file we are uploading using form
const multer = require("multer");
const Date = require('sequelize');
// Database model
const db = require("../models");
const sendMail = require("../services/emailServices");
const File = db.file;
// uuid
const { v4: uuid4 } = require("uuid");

// const exp = require("constants");

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    const uuid_for_file = uuidv4();
    file.uuid = uuid_for_file;
    const new_folder = `./temp/${uuid_for_file}/`;
    fs.mkdirSync(new_folder, { recursive: true });
    cb(null, new_folder);
  },
  filename: (req, file, cb) => cb(null, `${file.originalname}`),
});

const upload = multer({
  storage,
  limits: { fileSize: 1000000 * 100 },
}).single("myfile");

router.post("/", (req, res) => {
  upload(req, res, async (err) => {
    console.log("err: ", err);
    if (!req.file) {
      return res.status(400).send({ error: "File to be uploaded is missing!" });
    }
    if (err) {
      return res.status(500).send({ error: err.message });
    }
    console.log("file.uuid: ", req.file.uuid);
    await File.create({
      size: req.file.size,
      uuid: req.file.uuid,
      last_moment: db.sequelize.literal("now() + interval '1 day'"),
      status: db.status.Uploaded,
    }).then(response => {
      console.log("Creating new note in db about file with message:", response.dataValues);
      res.json({
        file: `${process.env.APP_BASE_URL}/files/${response.uuid}`,
      });
    })
    .catch(err => {
      console.log("Problem error:", err.message);
      res.status(500).send({ message: err.message });
    });
    console.log("Finish creating notes about new files");
  });
});

router.post("/send", async (req, res) => {
  const { uuid, emailTo, emailFrom } = req.body;

  // Validate request
  if (!uuid || !emailFrom || !emailTo) {
    res.status(422).send({ error: "All field are required!" });
  }
  await File.update(
    {
      receiver: emailTo,
      sender: emailFrom,
    },
    {
      where: {
        uuid: uuid
      }
    }
  ).then(response => {
    sendMail({
      from: emailFrom,
      to: emailTo,
      subject: `Spreader | ${emailFrom} shared a file with you`,
      text: `${emailFrom} shared a file with you`,
      html: require("../services/emailTemplate")({
        emailFrom: emailFrom,
        downloadLink: `${process.env.APP_BASE_URL}/files/${response.uuid}`,
        size: parseInt(response.size / 1000) + "KB",
        expires: "24 hours",
        BASE_URL: process.env.APP_BASE_URL,
      }),
    });
    res.send({ success: true, message: "Mail sent successfully" });
  }).catch(err => {
    console.log("Err: ", err);
    res.render("download", { error: "Link has been expired" });
  });
});

module.exports = router;
