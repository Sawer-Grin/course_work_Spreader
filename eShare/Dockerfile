FROM node:18-alpine

WORKDIR /user/src/app
COPY eShare/package*.json ./

RUN npm install
COPY eShare/. .

EXPOSE 8080
CMD [ "node", "server.js" ]