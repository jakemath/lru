#!/bin/bash
cd src
sudo docker-compose up -d --build
sudo docker-compose logs -f -t
