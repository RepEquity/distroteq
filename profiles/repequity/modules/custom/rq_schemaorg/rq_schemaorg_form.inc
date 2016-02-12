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

$rq_schemaorg_site_name = variable_get('schemaorg_name', '');
$rq_schemaorg_site_url = variable_get('schemaorg_url', '');
$rq_schemaorg_site_logo = variable_get('schemaorg_logo', '');
$rq_schemaorg_site_search_path = variable_get('schemaorg_search_path', '');
$rq_schemaorg_address_street = variable_get('schemaorg_address_street', '');
$rq_schemaorg_address_city = variable_get('schemaorg_address_city', '');
$rq_schemaorg_address_state = variable_get('schemaorg_address_state', '');
$rq_schemaorg_address_zip = variable_get('schemaorg_address_zip', '');
$rq_schemaorg_address_country = variable_get('schemaorg_address_country', '');
$rq_schemaorg_latitude = variable_get('schemaorg_latitude', '');
$rq_schemaorg_longitude = variable_get('schemaorg_longitude', '');
$rq_schemaorg_phone_number = variable_get('schemaorg_phone_number', '');
$rq_schemaorg_hours_Monday_opens = variable_get('schemaorg_hours_Monday_opens', '');
$rq_schemaorg_hours_Monday_closes = variable_get('schemaorg_hours_Monday_closes', '');
$rq_schemaorg_hours_Tuesday_opens = variable_get('schemaorg_hours_Tuesday_opens', '');
$rq_schemaorg_hours_Tuesday_closes = variable_get('schemaorg_hours_Tuesday_closes', '');
$rq_schemaorg_hours_Wednesday_opens = variable_get('schemaorg_hours_Wednesday_opens', '');
$rq_schemaorg_hours_Wednesday_closes = variable_get('schemaorg_hours_Wednesday_closes', '');
$rq_schemaorg_hours_Thursday_opens = variable_get('schemaorg_hours_Thursday_opens', '');
$rq_schemaorg_hours_Thursday_closes = variable_get('schemaorg_hours_Thursday_closes', '');
$rq_schemaorg_hours_Friday_opens = variable_get('schemaorg_hours_Friday_opens', '');
$rq_schemaorg_hours_Friday_closes = variable_get('schemaorg_hours_Friday_closes', '');
$rq_schemaorg_hours_Saturday_opens = variable_get('schemaorg_hours_Saturday_opens', '');
$rq_schemaorg_hours_Saturday_closes = variable_get('schemaorg_hours_Saturday_closes', '');
$rq_schemaorg_hours_Sunday_opens = variable_get('schemaorg_hours_Sunday_opens', '');
$rq_schemaorg_hours_Sunday_closes = variable_get('schemaorg_hours_Sunday_closes', '');

// Construct the social media profiles snippet
$social_media_profile =
<<<EOL

<script type="application/ld+json">
  // social media profiles
  {
    "@context" : "http://schema.org",
    "@type" : "Organization",
    "name" : "$rq_schemaorg_site_name",
    "url" : "$rq_schemaorg_site_url",
    "sameAs" : [
EOL;

for ($i = 0; $i <= $social_media_links_count; $i++) {
  $social_media_profile .= variable_get('schemaorg_social_media_entry_' . $i, '');
}

$social_media_profile .=
<<<EOL
      }
    ]
  }
</script>

EOL;

if ($social_media_links_count == 0) {
  $social_media_profile = '';
}

// Construct the logo snippet
$schema_logo =
<<<EOL

<script type="application/ld+json">
// logo
{
  "@context": "http://schema.org",
  "@type": "Organization",
  "url": "$rq_schemaorg_site_url",
  "logo": "$rq_schemaorg_site_logo"
}
</script>

EOL;

// Construct the search snippet
$schema_search =
<<<EOL

<script type="application/ld+json">
// Search
{
  "@context": "http://schema.org",
  "@type": "WebSite",
  "url": "$rq_schemaorg_site_url",
  "potentialAction": {
    "@type": "SearchAction",
    "target": "$rq_schemaorg_site_search_path",
    "query-input": "required name=search_term_string"
  }
}
</script>

EOL;

// Construct the LocalBusiness snippet
$schema_local_business =
<<<EOL

<script type="application/ld+json">
// LocalBusiness
{
  "@context": "http://schema.org",
  "@type": "LocalBusiness",
  "@id": "$rq_schemaorg_url",
  "name": "$rq_schemaorg_name",
  "address": {
    "@type": "PostalAddress",
    "streetAddress": "$rq_schemaorg_address_street",
    "addressLocality": "$rq_schemaorg_address_city",
    "addressRegion": "$rq_schemaorg_address_state",
    "postalCode": "$rq_schemaorg_address_zip",
    "addressCountry": "$rq_schemaorg_address_country"
  },
  "geo": {
    "@type": "GeoCoordinates",
    "latitude": $rq_schemaorg_latitude,
    "longitude": $rq_schemaorg_longitude
  },
  "url": "$rq_schemaorg_url",
  "telephone": "$rq_schemaorg_phone_number",
  "openingHoursSpecification": [
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Monday"
      ],
      "opens": "$rq_schemaorg_hours_Monday_opens",
      "closes": "$rq_schemaorg_hours_Monday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Tuesday"
      ],
      "opens": "$rq_schemaorg_hours_Tuesday_opens",
      "closes": "$rq_schemaorg_hours_Tuesday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Wednesday"
      ],
      "opens": "$rq_schemaorg_hours_Wednesday_opens",
      "closes": "$rq_schemaorg_hours_Wednesday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Thursday"
      ],
      "opens": "$rq_schemaorg_hours_Thursday_opens",
      "closes": "$rq_schemaorg_hours_Thursday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Friday"
      ],
      "opens": "$rq_schemaorg_hours_Friday_opens",
      "closes": "$rq_schemaorg_hours_Friday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Saturday"
      ],
      "opens": "$rq_schemaorg_hours_Saturday_opens",
      "closes": "$rq_schemaorg_hours_Saturday_closes"
    },
    {
      "@type": "OpeningHoursSpecification",
      "dayOfWeek": [
        "Sunday"
      ],
      "opens": "$rq_schemaorg_hours_Sunday_opens",
      "closes": "$rq_schemaorg_hours_Sunday_closes"
    }
  ]
}
</script>

EOL;


// Construct the reviews snippet
$schema_reviews =
<<<EOL

<script type="application/ld+json">
// Reviews
{
  "@context": "http://schema.org",
  "@type": "Website",
  "mainEntity": {
    "@type": "Organization",
    "aggregateRating": {
      "@type": "AggregateRating",
      "ratingValue": "$rq_schemaorg_reviews_aggregate_value",
      "reviewCount": "$rq_schemaorg_reviews_aggregate_count"
    },
    "review": [

EOL;

  // Loop over the reviews
  for ($i = 0; $i <= $reviews_count; $i++) {
    $temp_author = variable_get('schemaorg_review_author_' . $i, '');
    $temp_name = variable_get('schemaorg_review_name_' . $i, '');
    $temp_body = variable_get('schemaorg_review_body_' . $i, '');
    $temp_rating = variable_get('schemaorg_review_rating_' . $i, '');

$schema_reviews .=
<<<EOL

{
  "@type": "Review",
  "author": "$temp_author",
  "name": "$temp_name",
  "reviewBody": "$temp_body",
  "reviewRating": {
    "@type": "Rating",
    "ratingValue": "$temp_rating"
  }

EOL;

    // Check to see if this is the last item
    if ($i == $reviews_count) {
      $schema_reviews .= '}';
    }
    else {
      $schema_reviews .= '},';
    }
  }

$schema_reviews .=
<<<EOL

      ]
    }
  }
  </script>

EOL;

if ($reviews_count == 0) {
  $schema_reviews = '';
}

  $schemaorg_content =
<<<EOL
$social_media_profile
$schema_logo
$schema_local_business
$schema_reviews
EOL;

  // Add all compiled content to the primary variable for later recall
  variable_set('schemaorg_content', $schemaorg_content);
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