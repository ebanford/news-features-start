<?php

/**
 * Class definition for Camp Stories XML feed parser.
 *
 * Parses camp stories feed.
 */
class CampNewsXmlParser extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $feed = new SimpleXMLElement($fetcher_result->getRaw());

    $result = new FeedsParserResult();
    $result->title = 'CAMP News';
    $result->items = array();

    foreach ($feed->channel->item as $item) {
      $result->items[] = array(
        'title' => (string) $item->title,
        'callout' => '<p>'.(string) $item->description.'</p>', // wrap light_html in P tags
        'pubdate' => (string) $item->pubDate, // _parser_common_syndication_parse_date()
        'url' => (string) $item->link,
        'image_url' => (string) $item->thumb,
        'image_alt' => (string) $item->alt,
        'published' => 1,
        'tags' => array('camp'),
      );
    }

    return $result;
  }

  /**
   * Return mapping sources.
   */
  public function getMappingSources() {
    return array(
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the feed item.'),
      ),
      'callout' => array(
        'name' => t('Callout'),
        'description' => t('Description of the feed item.'),
      ),
      'pubdate' => array(
        'name' => t('Published date'),
        'description' => t('Published date as UNIX time GMT of the feed item.'),
      ),
      'url' => array(
        'name' => t('Item URL (link)'),
        'description' => t('URL of the feed item.'),
      ),
      'image_url' => array(
        'name' => t('Image URL'),
        'description' => t('URL of the feed item thumbnail image.'),
      ),
      'image_alt' => array(
        'name' => t('Image alt'),
        'description' => t('Alt text of the feed item thumbnail image.'),
      ),
      'published' => array(
        'name' => t('Published status'),
        'description' => t('Published status of the item.'),
      ),
      'tags' => array(
        'name' => t('Tags'),
        'description' => t('Keywords for the feed item.'),
      ),
    ) + parent::getMappingSources();
  }
}
