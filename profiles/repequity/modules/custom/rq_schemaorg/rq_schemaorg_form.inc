<?php
/**
 * @file
 * rq_schemaorg/rq_schemaorg.inc
 * Admin Form
 */

/**
 * Implements hook_form().
 */
function rq_schemaorg_form($form, &$form_state) {
  $form = array();

  $form['#tree'] = TRUE;

  $form['general_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Information'),
  );

    $form['general_information']['schemaorg_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Company Name'),
      '#default_value' => variable_get('schemaorg_name', ''),
      '#description' => t("Name of the company"),
      '#required' => FALSE,
    );

    $form['general_information']['schemaorg_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Website URL'),
      '#default_value' => variable_get('schemaorg_url', ''),
      '#description' => t("Website URL"),
      '#required' => FALSE,
    );

    $form['general_information']['schemaorg_logo'] = array(
      '#type' => 'textfield',
      '#title' => t('Website Logo Location'),
      '#default_value' => variable_get('schemaorg_logo', ''),
      '#description' => t("Absolute path to site logo (url)"),
      '#required' => FALSE,
    );

    $form['general_information']['schemaorg_search_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Search Path'),
      '#default_value' => variable_get('schemaorg_search_path', ''),
      '#description' => t("Search page path with {search_term_string} in place of string to be searching for (ex: http://www.thompsoncreek.com/search/node/{search_term_string})"),
      '#required' => FALSE,
    );

    $form['general_information']['schemaorg_phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone Number'),
      '#default_value' => variable_get('schemaorg_phone_number', ''),
      '#description' => t("Phone Number in this format: +18885840143"),
      '#required' => FALSE,
    );

  $form['social_media'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Media'),
    '#prefix' => '<div id="schemaorg-social-media-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['schemaorg_social_media_num_fields']) && variable_get('schemaorg_social_media_num_fields') != 1) {
    $form_state['schemaorg_social_media_num_fields'] = variable_get('schemaorg_social_media_num_fields');
  }

  for ($i = 0; $i < $form_state['schemaorg_social_media_num_fields']; $i++) {

    // Count to display on form
    $display_num = $i + 1;

    $form['social_media']['social_media_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Social Media Link'),
    );

    $form['social_media']['social_media_' . $i]['schemaorg_social_media_entry_' . $i][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Social Media Link @display_num',
                    array(
                      '@display_num' => check_plain($display_num)
                    )
                  ),
      '#default_value' => variable_get('schemaorg_social_media_entry_' . $i, ''),
      '#description' => t("Social Media URL"),
      '#required' => FALSE,
    );

  }

  $form['social_media']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more Social media Link'),
    '#submit' => array('schemaorg_social_media_form_add_one'),
    '#ajax' => array(
      'callback' => 'schemaorg_social_media_form_callback',
      'wrapper' => 'schemaorg-social-media-fieldset-wrapper',
    ),
  );

  if ($form_state['schemaorg_social_media_num_fields'] > 1) {
    $form['social_media']['remove_name'] = array(
      '#type' => 'submit',
      '#value' => t('Remove Social media Link'),
      '#submit' => array('schemaorg_social_media_form_remove_one'),
      '#ajax' => array(
        'callback' => 'schemaorg_social_media_form_callback',
        'wrapper' => 'schemaorg-social-media-fieldset-wrapper',
      ),
    );
  }

  $form['schemaorg_social_media_num_fields'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('schemaorg_social_media_num_fields', $form_state['schemaorg_social_media_num_fields'])
  );

  $form['location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Location'),
  );

    $form['location']['schemaorg_address_street'] = array(
      '#type' => 'textfield',
      '#title' => t('Street Address'),
      '#default_value' => variable_get('schemaorg_address_street', ''),
      '#description' => t("Street Address"),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_address_city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => variable_get('schemaorg_address_city', ''),
      '#description' => t("City or Address Locality"),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_address_state'] = array(
      '#type' => 'textfield',
      '#title' => t('State'),
      '#default_value' => variable_get('schemaorg_address_state', ''),
      '#description' => t("2 character State or Address Region"),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_address_zip'] = array(
      '#type' => 'textfield',
      '#title' => t('Zip code'),
      '#default_value' => variable_get('schemaorg_address_zip', ''),
      '#description' => t("5 digit Zipcode or Postal Code"),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_address_country'] = array(
      '#type' => 'textfield',
      '#title' => t('Country'),
      '#default_value' => variable_get('schemaorg_address_country', ''),
      '#description' => t("Two character representation of country."),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_longitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Longitude'),
      '#default_value' => variable_get('schemaorg_longitude', ''),
      '#description' => t("Longitude of business"),
      '#required' => FALSE,
    );

    $form['location']['schemaorg_latitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Latitude'),
      '#default_value' => variable_get('schemaorg_latitude', ''),
      '#description' => t("Latitude of business"),
      '#required' => FALSE,
    );

  $form['hours'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hours'),
  );

  // Define the days
  $days = array('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday');
  // Loop over the days
  for ($i = 0; $i <= 6; $i++) {
    $form['hours'][$days[$i]]['schemaorg_hours_' . $days[$i] . '_opens'] = array(
      '#type' => 'textfield',
      '#title' => t('@day Open Time', array('@day' => $days[$i])),
      '#default_value' => variable_get('schemaorg_hours_' . $days[$i] . '_opens', ''),
      '#description' => t("Military Time"),
      '#required' => FALSE,
    );

    $form['hours'][$days[$i]]['schemaorg_hours_' . $days[$i] . '_closes'] = array(
      '#type' => 'textfield',
      '#title' => t('@day Close Time', array('@day' => $days[$i])),
      '#default_value' => variable_get('schemaorg_hours_' . $days[$i] . '_closes', ''),
      '#description' => t("Military Time"),
      '#required' => FALSE,
    );
  }

  $form['reviews_aggregate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reviews Aggregate Information'),
  );

    $form['reviews_aggregate']['schemaorg_reviews_aggregate_value'] = array(
      '#type' => 'textfield',
      '#title' => t('Aggregate Rating Value'),
      '#default_value' => variable_get('schemaorg_reviews_aggregate_value', ''),
      '#description' => t("Aggregate Rating Value"),
      '#required' => FALSE,
    );

    $form['reviews_aggregate']['schemaorg_reviews_aggregate_count'] = array(
      '#type' => 'textfield',
      '#title' => t('Aggregate Review Count'),
      '#default_value' => variable_get('schemaorg_reviews_aggregate_count', ''),
      '#description' => t("Aggregate Review Count"),
      '#required' => FALSE,
    );


  $form['reviews'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reviews'),
    '#prefix' => '<div id="schemaorg-reviews-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['schemaorg_reviews_num_fields']) && variable_get('schemaorg_reviews_num_fields') != 1) {
    $form_state['schemaorg_reviews_num_fields'] = variable_get('schemaorg_reviews_num_fields');
  }

  for ($i = 0; $i < $form_state['schemaorg_reviews_num_fields']; $i++) {

    // Count to display on form
    $display_num = $i + 1;

    $form['reviews']['review_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Review'),
    );

    $form['reviews']['review_' . $i]['schemaorg_review_author_' . $i][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Review Author'),
      '#default_value' => variable_get('schemaorg_review_author_' . $i, ''),
      '#description' => t("Review Author"),
      '#required' => FALSE,
    );

    $form['reviews']['review_' . $i]['schemaorg_review_name_' . $i][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Review Name'),
      '#default_value' => variable_get('schemaorg_review_name_' . $i, ''),
      '#description' => t("Review Name"),
      '#required' => FALSE,
    );

    $form['reviews']['review_' . $i]['schemaorg_review_body_' . $i][$i] = array(
      '#type' => 'textarea',
      '#title' => t('Review Body'),
      '#default_value' => variable_get('schemaorg_review_body_' . $i, ''),
      '#description' => t("Review Body"),
      '#required' => FALSE,
    );

    $form['reviews']['review_' . $i]['schemaorg_review_rating_' . $i][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Review Rating'),
      '#default_value' => variable_get('schemaorg_review_rating_' . $i, ''),
      '#description' => t("Review Rating"),
      '#required' => FALSE,
    );

  }

  $form['reviews']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more Review'),
    '#submit' => array('schemaorg_reviews_form_add_one'),
    '#ajax' => array(
      'callback' => 'schemaorg_reviews_form_callback',
      'wrapper' => 'schemaorg-reviews-fieldset-wrapper',
    ),
  );

  if ($form_state['schemaorg_reviews_num_fields'] > 1) {
    $form['reviews']['remove_name'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one review'),
      '#submit' => array('schemaorg_reviews_form_remove_one'),
      '#ajax' => array(
        'callback' => 'schemaorg_reviews_form_callback',
        'wrapper' => 'schemaorg-reviews-fieldset-wrapper',
      ),
    );
  }

  $form['schemaorg_reviews_num_fields'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('schemaorg_reviews_num_fields', $form_state['schemaorg_reviews_num_fields'])
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Tags'),
  );

  return $form;
}

/**
 * Implements hook_form_add_one().
 */
function schemaorg_social_media_form_add_one($form, &$form_state) {
  $form_state['schemaorg_social_media_num_fields']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_callback().
 */
function schemaorg_social_media_form_callback($form, $form_state) {
  return $form['social_media'];
}

/**
 * Implements hook_form_remove_one().
 */
function schemaorg_social_media_form_remove_one($form, &$form_state) {
  if ($form_state['schemaorg_social_media_num_fields'] > 1) {
    $form_state['schemaorg_social_media_num_fields']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_add_one().
 */
function schemaorg_reviews_form_add_one($form, &$form_state) {
  $form_state['schemaorg_reviews_num_fields']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_callback().
 */
function schemaorg_reviews_form_callback($form, $form_state) {
  return $form['reviews'];
}

/**
 * Implements hook_form_remove_one().
 */
function schemaorg_reviews_form_remove_one($form, &$form_state) {
  if ($form_state['schemaorg_reviews_num_fields'] > 1) {
    $form_state['schemaorg_reviews_num_fields']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_submit().
 */
function rq_schemaorg_form_submit($form, &$form_state) {

  // Initialize our output variable
  $output = '';
  $front_output = '';

  variable_set('schemaorg_social_media_num_fields', $form_state['values']['schemaorg_social_media_num_fields']);
  variable_set('schemaorg_reviews_num_fields', $form_state['schemaorg_reviews_num_fields']);

  // Store all of our data so it can be recalled in the form later
  variable_set('schemaorg_name', $form_state['values']['general_information']['schemaorg_name']);
  variable_set('schemaorg_url', $form_state['values']['general_information']['schemaorg_url']);
  variable_set('schemaorg_logo', $form_state['values']['general_information']['schemaorg_logo']);
  variable_set('schemaorg_search_path', $form_state['values']['general_information']['schemaorg_search_path']);
  variable_set('schemaorg_phone_number', $form_state['values']['general_information']['schemaorg_phone_number']);

  // Count the number of submitted social media links
  $social_media_links_count = variable_get('schemaorg_social_media_num_fields', '');
  // Loop over the social media links
  for ($i = 0; $i <= $social_media_links_count; $i++) {
    variable_set('schemaorg_social_media_entry_' . $i, $form_state['values']['social_media']['social_media_' . $i]['schemaorg_social_media_entry_' . $i][$i]);
  }

  // Address information
  variable_set('schemaorg_address_street', $form_state['values']['location']['schemaorg_address_street']);
  variable_set('schemaorg_address_city', $form_state['values']['location']['schemaorg_address_city']);
  variable_set('schemaorg_address_state', $form_state['values']['location']['schemaorg_address_state']);
  variable_set('schemaorg_address_zip', $form_state['values']['location']['schemaorg_address_zip']);
  variable_set('schemaorg_address_country', $form_state['values']['location']['schemaorg_address_country']);

  // GPS Coordinates
  variable_set('schemaorg_longitude', $form_state['values']['location']['schemaorg_longitude']);
  variable_set('schemaorg_latitude', $form_state['values']['location']['schemaorg_latitude']);

  // Define the days
  $days = array('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday');
  // Loop over the days
  for ($i = 0; $i <= 6; $i++) {
    // Add the opening time
    variable_set('schemaorg_hours_' . $days[$i] . '_opens', $form_state['values']['hours'][$days[$i]]['schemaorg_hours_' . $days[$i] . '_opens']);
    // Add the closing time
    variable_set('schemaorg_hours_' . $days[$i] . '_closes', $form_state['values']['hours'][$days[$i]]['schemaorg_hours_' . $days[$i] . '_closes']);
  }

  // Add the reviews aggragate value and count
  variable_set('schemaorg_reviews_aggregate_value', $form_state['values']['reviews_aggregate']['schemaorg_reviews_aggregate_value']);
  variable_set('schemaorg_reviews_aggregate_count', $form_state['values']['reviews_aggregate']['schemaorg_reviews_aggregate_count']);

  // Count the number of submitted reviews
  $reviews_count = variable_get('schemaorg_reviews_num_fields', '');
  // Loop over the reviews
  for ($i = 0; $i <= $reviews_count; $i++) {
    variable_set('schemaorg_review_author_' . $i, $form_state['values']['reviews']['review_' . $i]['schemaorg_review_author_' . $i][$i]);
    variable_set('schemaorg_review_name_' . $i, $form_state['values']['reviews']['review_' . $i]['schemaorg_review_name_' . $i][$i]);
    variable_set('schemaorg_review_body_' . $i, $form_state['values']['reviews']['review_' . $i]['schemaorg_review_body_' . $i][$i]);
    variable_set('schemaorg_review_rating_' . $i, $form_state['values']['reviews']['review_' . $i]['schemaorg_review_rating_' . $i][$i]);
  }

  // Construct the social media profiles snippet
  $social_media_profile = '';
  $social_media_profile .= '<script type="application/ld+json">';
  $social_media_profile .= '// social media profiles';
  $social_media_profile .= '{';
  $social_media_profile .= '  "@context" : "http://schema.org",';
  $social_media_profile .= '  "@type" : "Organization",';
  $social_media_profile .= '  "name" : "' . variable_get('schemaorg_name', '') . '",';
  $social_media_profile .= '  "url" : "' . variable_get('schemaorg_url', '') . '",';
  $social_media_profile .= '  "sameAs" : [';
  for ($i = 0; $i <= $social_media_links_count; $i++) {
    $social_media_profile .= variable_get('schemaorg_social_media_entry_' . $i, '');
  }
  $social_media_profile .= '  ]';
  $social_media_profile .= '}';
  $social_media_profile .= '</script>';

  // Construct the logo snippet
  $schema_logo = '';
  $schema_logo .= '<script type="application/ld+json">';
  $schema_logo .= '// logo';
  $schema_logo .= '{';
  $schema_logo .= '  "@context": "http://schema.org",';
  $schema_logo .= '  "@type": "Organization",';
  $schema_logo .= '  "url": "' . variable_get('schemaorg_url', '') . '",';
  $schema_logo .= '  "logo": "' . variable_get('schemaorg_logo', '') . '"';
  $schema_logo .= '}';
  $schema_logo .= '</script>';

  // Construct the search snippet
  $schema_search = '';
  $schema_search .= '<script type="application/ld+json">';
  $schema_search .= '// Search';
  $schema_search .= '{';
  $schema_search .= '  "@context": "http://schema.org",';
  $schema_search .= '  "@type": "WebSite",';
  $schema_search .= '  "url": "' . variable_get('schemaorg_url', '') . '",';
  $schema_search .= '  "potentialAction": {';
  $schema_search .= '    "@type": "SearchAction",';
  $schema_search .= '    "target": "' . variable_get('schemaorg_search_path', '') . '",';
  $schema_search .= '    "query-input": "required name=search_term_string"';
  $schema_search .= '  }';
  $schema_search .= '}';
  $schema_search .= '</script>';

  // Construct the LocalBusiness snippet
  $schema_local_business = '<script type="application/ld+json">';
  $schema_local_business .= '// LocalBusiness';
  $schema_local_business .= '{';
  $schema_local_business .= '  "@context": "http://schema.org",';
  $schema_local_business .= '  "@type": "LocalBusiness",';
  $schema_local_business .= '  "@id": "' . variable_get('schemaorg_url', '') . '",';
  $schema_local_business .= '  "name": "' . variable_get('schemaorg_name', '') . '",';
  $schema_local_business .= '  "address": {';
  $schema_local_business .= '    "@type": "PostalAddress",';
  $schema_local_business .= '    "streetAddress": "' . variable_get('schemaorg_address_street', '') . '",';
  $schema_local_business .= '    "addressLocality": "' . variable_get('schemaorg_address_city', '') . '",';
  $schema_local_business .= '    "addressRegion": "' . variable_get('schemaorg_address_state', '') . '",';
  $schema_local_business .= '    "postalCode": "' . variable_get('schemaorg_address_zip', '') . '",';
  $schema_local_business .= '    "addressCountry": "' . variable_get('schemaorg_address_country', '') . '"';
  $schema_local_business .= '  },';
  $schema_local_business .= '  "geo": {';
  $schema_local_business .= '    "@type": "GeoCoordinates",';
  $schema_local_business .= '    "latitude": ' . variable_get('schemaorg_latitude', '') . ',';
  $schema_local_business .= '    "longitude": ' . variable_get('schemaorg_longitude', '') . '';
  $schema_local_business .= '  },';
  $schema_local_business .= '  "url": "' . variable_get('schemaorg_url', '') . '",';
  $schema_local_business .= '  "telephone": "' . variable_get('schemaorg_phone_number', '') . '",';
  $schema_local_business .= '  "openingHoursSpecification": [';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Monday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Monday_opens', '') . '"';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Monday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Tuesday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Tuesday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Tuesday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Wednesday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Wednesday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Wednesday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Thursday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Thursday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Thursday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Friday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Friday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Friday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Saturday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Saturday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Saturday_closes', '') . '"';
  $schema_local_business .= '    },';
  $schema_local_business .= '    {';
  $schema_local_business .= '      "@type": "OpeningHoursSpecification",';
  $schema_local_business .= '      "dayOfWeek": [';
  $schema_local_business .= '        "Sunday"';
  $schema_local_business .= '      ],';
  $schema_local_business .= '      "opens": "' . variable_get('schemaorg_hours_Sunday_opens', '') . '",';
  $schema_local_business .= '      "closes": "' . variable_get('schemaorg_hours_Sunday_closes', '') . '"';
  $schema_local_business .= '    }';
  $schema_local_business .= '  ]';
  $schema_local_business .= '}';
  $schema_local_business .= '</script>';

  // Construct the reviews snippet
  $schema_reviews = '<script type="application/ld+json">';
  $schema_reviews .= '// Reviews';
  $schema_reviews .= '{';
  $schema_reviews .= '  "@context": "http://schema.org",';
  $schema_reviews .= '  "@type": "Website",';
  $schema_reviews .= '  "mainEntity": {';
  $schema_reviews .= '    "@type": "Organization",';
  $schema_reviews .= '    "aggregateRating": {';
  $schema_reviews .= '      "@type": "AggregateRating",';
  $schema_reviews .= '      "ratingValue": "' . variable_get('schemaorg_reviews_aggregate_value', '') . '",';
  $schema_reviews .= '      "reviewCount": "' . variable_get('schemaorg_reviews_aggregate_count', '') . '"';
  $schema_reviews .= '    },';
  $schema_reviews .= '    "review": [';

  // Count the number of submitted reviews
  $reviews_count = count($form_state['values']['reviews']);
  // Loop over the reviews
  for ($i = 0; $i < $reviews_count; $i++) {
    $schema_reviews .= '      {';
    $schema_reviews .= '        "@type": "Review",';
    $schema_reviews .= '        "author": "' . variable_get('schemaorg_review_author_' . $i, '') . '",';
    $schema_reviews .= '        "name": "' . variable_get('schemaorg_review_name_' . $i, '') . '",';
    $schema_reviews .= '        "reviewBody": "' . variable_get('schemaorg_review_body_' . $i, '') . '",';
    $schema_reviews .= '        "reviewRating": {';
    $schema_reviews .= '          "@type": "Rating",';
    $schema_reviews .= '          "ratingValue": "' . variable_get('schemaorg_review_rating_' . $i, '') . '"';
    $schema_reviews .= '        }';
    // Check to see if this is the last item
    if ($i == $reviews_count) {
      $schema_reviews .= '      }';
    }
    else {
      $schema_reviews .= '      },';
    }
  }

  $schema_reviews .= '    ]';
  $schema_reviews .= '  }';
  $schema_reviews .= '}';
  $schema_reviews .= '</script>';

  // Add all compiled content to the primary variable for later recall
  variable_set('schemaorg_content', $social_media_profile . $schema_logo . $schema_local_business . $schema_reviews);
  variable_set('schemaorg_content_front_only', $schema_search);

  drupal_set_message(t('Form submitted!'));
}

/**

<script type="application/ld+json">
// social media profiles
{
  "@context" : "http://schema.org",
  "@type" : "Organization",
  "name" : "Thompson Creek Windows",
  "url" : "http://www.thompsoncreek.com/",
  "sameAs" : [
    "https://www.facebook.com/thompsoncreek",
    "https://twitter.com/ThompsonCreek",
    "https://plus.google.com/b/104315293959354988055/104315293959354988055/posts/p/pub",
    "http://www.linkedin.com/company/thompson-creek-window-company",
    "https://www.youtube.com/user/ThompsonCreekWindows",
    "http://www.pinterest.com/thompsoncreek/",
    "http://instagram.com/thompsoncreekwindows/"
  ]
}
</script>

<script type="application/ld+json">
// logo
{
  "@context": "http://schema.org",
  "@type": "Organization",
  "url": "http://www.thompsoncreek.com",
  "logo": "http://www.thompsoncreek.com/sites/all/themes/thompson_creek_2014/images/tcw-logo.png"
}
</script>

<script type="application/ld+json">
// Search
{
  "@context": "http://schema.org",
  "@type": "WebSite",
  "url": "http://www.thompsoncreek.com/",
  "potentialAction": {
    "@type": "SearchAction",
    "target": "http://www.thompsoncreek.com/search/node/{search_term_string}",
    "query-input": "required name=search_term_string"
  }
}
</script>

<script type="application/ld+json">
// LocalBusiness
{
  "@context": "http://schema.org",
  "@type": "LocalBusiness",
  "@id": "http://www.thompsoncreek.com/",
  "name": "Thompson Creek Window Company",
  "address": {
    "@type": "PostalAddress",
    "streetAddress": "5000 Philadelphia Way",
    "addressLocality": "Lanham",
    "addressRegion": "MD",
    "postalCode": "20706",
    "addressCountry": "US"
  },
  "geo": {
    "@type": "GeoCoordinates",
    "latitude": 38.958688,
    "longitude": -76.838707
  },
  "url": "http://www.thompsoncreek.com/",
  "telephone": "+18885840143",
  "openingHoursSpecification": [
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
      ],
      "opens": "08:00",
      "closes": "21:00"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Saturday",
        "Sunday"
      ],
      "opens": "8:00",
      "closes": "18:00"
    }
  ]
}
</script>

<script type="application/ld+json">
// Reviews
{
  "@context": "http://schema.org",
  "@type": "Website",
  "mainEntity": {
    "@type": "Organization",
    "aggregateRating": {
      "@type": "AggregateRating",
      "ratingValue": "4.7",
      "reviewCount": "4719"
    },
    "review": [
      {
        "@type": "Review",
        "author": "Jacquelyn R.",
        "name": "Review by Jacquelyn R. of Gaithersburg, MD",
        "reviewBody": "Excellent and professional service from beginning to end! The product is like a beautiful piece of furniture! It totally upgrades the house with the new door! The installation team were so efficient and gentleman!",
        "reviewRating": {
          "@type": "Rating",
          "ratingValue": "5"
        }
      },
      {
        "@type": "Review",
        "author": "Charles T.",
        "name": "Review by Charles T. of Severn, MD",
        "reviewBody": "We purchased inner French doors and storm door (with the doggie door entry) and we are thoroughly satisfied. Originally, we thought the doors were not going to be big enough for our large dog. Not once did Thompson Creek became irate or irritable, instead the QA came to look at the door and our dog and we agreed to try it out and if there was going to be a problem, they were standing by to change it. Doors works great. We are satisfied customers and our dogs are happy too.",
        "reviewRating": {
          "@type": "Rating",
          "ratingValue": "5"
        }
      }
    ]
  }
}
</script>

https://developers.google.com/structured-data/testing-tool/

 */