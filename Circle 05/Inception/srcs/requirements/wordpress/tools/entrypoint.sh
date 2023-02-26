#! /bin/bash

# Download wordpress:
# https://wordpress.org/documentation/article/how-to-install-wordpress/
# https://wordpress.org/documentation/article/creating-database-for-wordpress/
# https://www.cloudways.com/blog/install-wordpress-using-wp-cli/
# https://make.wordpress.org/cli/handbook/how-to/how-to-install/
# https://wordpress.org/documentation/article/how-to-install-wordpress/

#sleep ${SLEEP_TIME}	# To ensure that mysql is running

if [ -f "wp-config.php" ]; then	#alt: wp core is-installed --allow-root
	echo "WordPress: already installed"
else
	echo "WordPress: creating config file"
	wp config create --allow-root \
		--dbname=${MYSQL_NAME} \
		--dbuser=${MYSQL_USER} \
		--dbpass=${MYSQL_PASSWORD} \
		--dbhost=${MYSQL_HOST}

	echo "WordPress: installing"
	wp core install --allow-root \
		--url=${WP_URL} \
		--title=${WP_TITLE} \
		--admin_user=${WP_ADMIN_NAME} \
		--admin_password=${WP_ADMIN_PASSWORD} \
		--admin_email=${WP_ADMIN_EMAIL}

	echo "WordPress: creating user"
	wp user create --allow-root \
		${WP_USER_NAME} ${WP_USER_EMAIL} \
		--role=${WP_USER_ROLE} \
		--user_pass=${WP_USER_PASSWORD}
	
	# If Redis in bonus is set up
	if [ ${REDIS_BONUS} -eq 1 ]; then
		# Adjust config to communicate with redis server
		wp config set WP_REDIS_HOST 'redis' --type=constant --allow-root
		wp config set WP_REDIS_PORT 6379 --type=constant --allow-root
		wp config set WP_CACHE true --type=constant --allow-root
		wp config set WP_CACHE_KEY_SALT '${WP_URL}' --type=constant --allow-root

		# Install the redis plugin for wordpress
		wp plugin install redis-cache --activate --allow-root
		wp redis enable --allow-root
	fi
	
	chown -R www-data:www-data /var/www/html
	chmod -R 775 /var/www/html
	chmod -R g+w /var/www/html

fi

/usr/sbin/php-fpm7.3 -R -F