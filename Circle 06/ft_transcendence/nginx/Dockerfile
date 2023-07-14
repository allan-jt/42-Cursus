FROM nginx:1.23

# Define the word to be replaced and the replacement word
ARG word_to_replace='HOST_URL'
ARG HOST_URL
ARG FE_PORT
ARG BE_PORT

# Replace default config file
COPY ./default.conf /etc/nginx/conf.d/default.conf

# Run the word replacement command in the container
RUN sed -i "s/$word_to_replace/$HOST_URL/g" /etc/nginx/conf.d/default.conf
RUN sed -i "s/FE_PORT/$FE_PORT/g" /etc/nginx/conf.d/default.conf
RUN sed -i "s/BE_PORT/$BE_PORT/g" /etc/nginx/conf.d/default.conf

CMD ["nginx", "-g", "daemon off;"]
